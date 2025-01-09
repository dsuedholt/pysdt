# PySDT: Python bindings for the Sound Design Toolkit

Thin Python bindings for the [Sound Design Toolkit (SDT)](https://github.com/SkAT-VG/SDT) library.

The bindings consist of two parts:
- C++ wrapper classes (contained in `src/wrappers/`) encapsulate SDT's C API, especially the manual memory management
- [nanobind](https://github.com/wjakob/nanobind) bindings (contained in `src/pysdt.cpp`) make the wrappers available in Python

Proper documentation for the Python library will be added at some point. Until then, refer to examples below. The [SDT documentation](https://skat-vg.github.io/SDT/) should be helpful as well, since the bindings follow the C API and module structure very closely. Getter/setter pairs are usually captured as Python `@properties`.

## Features

Most of the SDT functionality is available in the bindings, **except for** 
- OSC support
- JSON export/import
- anything with a straightforward `numpy` equivalent, e.g. array means or FFT calculation

## Installation

Packaged wheels are available for Linux, MacOS and Windows.

```
pip install pysdt
```

Alternatively, you can build the bindings yourself. The SDT is included as a submodule in this repository (with slight modifications to ensure MSVC compatibility). Two submodules of the SDT itself will need to be initialized as well.

```
git clone git@github.com:dsuedholt/pysdt.git
cd pysdt && git submodule update --init SDT
cd SDT && git submodule update --init 3rdparty/json-builder 3rdparty/json-parser
cd .. && pip install .
```

## Usage

By default, **the global sampling rate is set to 0 Hz**. It is important to set the global sampling rate explicitly at the start of your script. If you change the sampling rate later on, you may need to call `update()` on some objects; check the [SDT documentation](https://skat-vg.github.io/SDT/).

Here's a brief example of using the `DCMotor` class to generate one second of engine sound:

```python
import pysdt
import numpy as np

sr = 44100
pysdt.common.set_samplerate(sr)

# buffer length of an internal comb filter is a constructor argument
motor = pysdt.dcmotor.DCMotor(1024)

# properties bind to getRpm / setRpm etc
motor.rpm = 4000
motor.load = 0.2

# motor.gear_ratio = ...
# motor.coils = ...
# see https://skat-vg.github.io/SDT/group__dcmotor.html for more parameters

audio = np.zeros(sr)
for i in range(sr):
    audio[i] = motor.dsp()

# we have sound! can now process, play or save it, e.g:
import soundfile as sf
sf.write("engine.wav", audio, sr)
```

### `dsp(...)` methods

Most SDT classes have a `dsp()` method that expects to be called once per sample, but the signature can vary. Here are some examples that demonstrate how PySDT wraps these depending on their signature in the C API.

```python
import pysdt
import numpy as np

sr = 44100
pysdt.common.set_samplerate(sr)

audio = np.zeros(sr)

# C signature: double dsp(...)
# return single floating point number
bubble = pysdt.liquids.Bubble()
bubble.radius = 0.001
bubble.rise_factor = 0.1
bubble.depth = 0.7

rev = pysdt.effects.Reverb(sr)
rev.time = 0.5
rev.update()

for i in range(sr):
    if i % (sr // 4) == 0:
        bubble.trigger()
    bubble_out = bubble.dsp()
    audio[i] = rev.dsp(bubble_out * 100)


# C signature: void dsp(..., double *out, ...)
# return multiple floating point numbers
expl = pysdt.gases.Explosion(sr, sr)
expl.blast_time = 0.1
expl.scatter_time = 4
expl.dispersion = 0.5
expl.distance = 10
expl.wave_speed = 340.2
expl.wind_speed = 600

expl.trigger()

for i in range(sr):
    wave, wind = expl.dsp()
    audio[i] = 0.5 * wave + 0.5 * wind

# C signature: int dsp(..., double *out, double in)
# This one is mostly used in SDTAnalysis / pysdt.analysis
# It expects to be called every sample,
# but will only provide output when a frame has been filled
# returns Tuple[bool, np.ndarray[float]]
audio = np.cos(440 * 2 * np.pi * np.arange(sr) / sr) # simple sine wave
win_size = 1024
pitch = pysdt.analysis.Pitch(win_size)
pitch.overlap = 0.5

f0s, confs = [], []
for i in range(sr):
    has_values, values = pitch.dsp(audio[i])
    if has_values:
        f0, conf = values
        f0s.append(f0)
        confs.append(conf)
```

### Interactions

Interactors apply forces to resonators and can optionally couple two resonators together. Internally, the `dsp()` method of an interactor will call the `dsp()` method of the resonators it interacts with. After the interactor's `dsp()` method was called, audio can be read from the position value of the resonators' pickups. 

The following code replicates the example shown in the helpfile of the Pd `scraping~` object:

```python
import pysdt
import numpy as np

sr = 44100
pysdt.common.set_samplerate(sr)

audio = np.zeros(sr)

n_modes = 3
n_pickups = 1

res = pysdt.resonators.Resonator(n_modes, n_pickups)

freqs = [500, 1300, 1700]
decays = [0.03, 0.02, 0.01]
pickups = [100, 100, 100]
weights = [1, 1, 1]

res.active_modes = 3

for i in range(n_modes):
    res.set_frequency(i, freqs[i])
    res.set_decay(i, decays[i])
    res.set_gain(0, i, pickups[i])
    res.set_weight(i, weights[i])

res.fragment_size = 1

res.update()

impact = pysdt.interactors.Impact()
impact.stiffness = 1e8
impact.dissipation = 0.8
impact.shape = 1.5

impact.first_point = 0
impact.second_point = 0

impact.first_resonator = res

scraping = pysdt.control.Scraping()
scraping.velocity = 1
scraping.grain = 0.001
scraping.force = 2

lop = pysdt.filters.OnePole()
lop.lowpass(20)

for i in range(sr):
    noise = pysdt.oscillators.white_noise()
    scrape_force = scraping.dsp(lop.dsp(noise)) * 10
    impact.dsp(scrape_force, 0, 0, 0, 0, 0)
    audio[i] = res.get_position(0) * 50000
```