# PySDT: Python bindings for the Sound Design Toolkit

Thin Python bindings for the [Sound Design Toolkit (SDT)](https://github.com/SkAT-VG/SDT) library.

The bindings consist of two parts:
- C++ wrapper classes (contained in `src/wrappers/`) encapsulate SDT's C API, especially the manual memory management
- [nanobind](https://github.com/wjakob/nanobind) bindings (contained in `src/pysdt.cpp`) make the wrappers available in Python

Proper documentation for the Python library will be added at some point. Until then, the [SDT documentation](https://skat-vg.github.io/SDT/) should be helpful as well, since the bindings follow the C API and module structure very closely. Getter/setter pairs are usually captured as Python `@properties`.

### Features

Most of the SDT functionality is available in the bindings, **except for** 
- OSC support
- JSON export/import
- anything with a straightforward `numpy` equivalent, e.g. array means or FFT calculation

### Installation

Packaged wheels are available for Linux and MacOS.

```
pip install pysdt
```

Alternatively, you can build the bindings yourself:

```
git clone git@github.com:dsuedholt/pysdt.git && cd pysdt
pip install .
```

Currently, a pre-built dynamic library for the respective platform is downloaded at build-time and packaged together with the Python bindings. This works but has some limitations, I haven't quite figured out how to make it work for Windows. In the future, I should probably move towards building the SDT from source.

### Usage

By default, **the global sampling rate is set to 0 Hz**. It is important to set the global sampling rate explicitly at the start of your script. If you change the sampling rate later on, you may need to call `update()` on some objects; check the [SDT documentation](https://skat-vg.github.io/SDT/).

Here's a brief example of using the `DCMotor` class to generate one second of engine sound:

```python
import pysdt
import numpy as np

sr = 44100

pysdt.common.set_sampling_rate(sr)

# buffer length of an internal comb filter is a constructor argument
motor = pysdt.dcmotor.DCMotor(1024)

# properties bind to getRpm / setRpm etc
motor.rpm = 3000
motor.load = 0.5

result = np.zeros(sr)
for i in range(sr):
    result[i] = motor.dsp()

# we have sound! can now process, play or save it, e.g:
import soundfile as sf
sf.write("engine.wav", result, sr)
```