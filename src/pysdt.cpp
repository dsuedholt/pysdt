#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/pair.h>
#include <nanobind/stl/array.h>

#include <SDTCommon.h>

#include "wrappers/Analysis.h"
#include "wrappers/Control.h"
#include "wrappers/DCMotor.h"
#include "wrappers/Demix.h"
#include "wrappers/Effects.h"
#include "wrappers/Filters.h"
#include "wrappers/Gases.h"
#include "wrappers/Interactors.h"
#include "wrappers/Liquids.h"
#include "wrappers/Motor.h"
#include "wrappers/Oscillators.h"
#include "wrappers/Resonators.h"

#include "BindingMacros.h"

namespace nb = nanobind;
using namespace nb::literals;

using arr1d = nb::ndarray<double, nb::ndim<1>>;

using namespace sdtwrappers;

void add_analysis_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("analysis");

    nb::class_<Pitch>(m, "Pitch")
        .def(nb::init<unsigned int>())
        .SDT_BIND_PROPERTY_RW(size, Pitch, Size, unsigned int)
        .SDT_BIND_PROPERTY_RW(overlap, Pitch, Overlap, double)
        .SDT_BIND_PROPERTY_RW(tolerance, Pitch, Tolerance, double)
        .def("dsp", &Pitch::dsp);

    nb::class_<Myoelastic>(m, "Myoelastic")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(dc_frequency, Myoelastic, DcFrequency, double)
        .SDT_BIND_PROPERTY_RW(low_frequency, Myoelastic, LowFrequency, double)
        .SDT_BIND_PROPERTY_RW(high_frequency, Myoelastic, HighFrequency, double)
        .SDT_BIND_PROPERTY_RW(threshold, Myoelastic, Threshold, double)
        .def("update", &Myoelastic::update)
        .def("dsp", &Myoelastic::dsp);

    nb::class_<SpectralFeats>(m, "SpectralFeats")
        .def(nb::init<unsigned int>())
        .SDT_BIND_PROPERTY_RW(max_freq, SpectralFeats, MaxFreq, double)
        .SDT_BIND_PROPERTY_RW(min_freq, SpectralFeats, MinFreq, double)
        .SDT_BIND_PROPERTY_RW(overlap, SpectralFeats, Overlap, double)
        .SDT_BIND_PROPERTY_RW(size, SpectralFeats, Size, unsigned int)
        .def("dsp", &SpectralFeats::dsp);

    nb::class_<ZeroCrossing>(m, "ZeroCrossing")
        .def(nb::init<unsigned int>())
        .SDT_BIND_PROPERTY_RW(overlap, ZeroCrossing, Overlap, double)
        .SDT_BIND_PROPERTY_RW(size, ZeroCrossing, Size, unsigned int)
        .def("dsp", &ZeroCrossing::dsp);
}

void add_control_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("control");

    nb::class_<Bouncing>(m, "Bouncing")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(restitution, Bouncing, Restitution, double)
        .SDT_BIND_PROPERTY_RW(height, Bouncing, Height, double)
        .SDT_BIND_PROPERTY_RW(irregularity, Bouncing, Irregularity, double)
        .def("reset", &Bouncing::reset)
        .def("dsp", &Bouncing::dsp)
        .def("has_finished", &Bouncing::hasFinished);

    nb::class_<Breaking>(m, "Breaking")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(stored_energy, Breaking, StoredEnergy, double)
        .SDT_BIND_PROPERTY_RW(crushing_energy, Breaking, CrushingEnergy, double)
        .SDT_BIND_PROPERTY_RW(granularity, Breaking, Granularity, double)
        .SDT_BIND_PROPERTY_RW(fragmentation, Breaking, Fragmentation, double)
        .def("reset", &Breaking::reset)
        .def("dsp", &Breaking::dsp)
        .def("has_finished", &Breaking::hasFinished);

    nb::class_<Crumpling>(m, "Crumpling")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(crushing_energy, Crumpling, CrushingEnergy, double)
        .SDT_BIND_PROPERTY_RW(granularity, Crumpling, Granularity, double)
        .SDT_BIND_PROPERTY_RW(fragmentation, Crumpling, Fragmentation, double)
        .def("dsp", &Crumpling::dsp);

    nb::class_<Rolling>(m, "Rolling")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(energy, Rolling, Grain, double)
        .SDT_BIND_PROPERTY_RW(size, Rolling, Depth, double)
        .SDT_BIND_PROPERTY_RW(speed, Rolling, Mass, double)
        .SDT_BIND_PROPERTY_RW(speed, Rolling, Velocity, double)
        .def("dsp", &Rolling::dsp);

    nb::class_<Scraping>(m, "Scraping")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(energy, Scraping, Grain, double)
        .SDT_BIND_PROPERTY_RW(size, Scraping, Force, double)
        .SDT_BIND_PROPERTY_RW(speed, Scraping, Velocity, double)
        .def("dsp", &Scraping::dsp);
}

void add_common_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("common");

    m.attr("SDT_VERSION") = STRINGIFY(SDT_ver);
    m.attr("MACH1") = SDT_MACH1;
    m.attr("EARTH") = SDT_EARTH;
    m.attr("MICRO") = SDT_MICRO;
    m.attr("QUIET") = SDT_QUIET;

    m.def("blackman",
        [] (arr1d& sig) {
            SDT_blackman(sig.data(), static_cast<int>(sig.size()));
        });
    m.def("exp_rand", &SDT_expRand);
    m.def("gaussian_1d", &SDT_gaussian1D);
    m.def("gravity", &SDT_gravity);

    m.def("haar",
        [] (arr1d& sig) {
            SDT_haar(sig.data(), static_cast<int>(sig.size()));
        });

    m.def("hanning",
        [] (arr1d& sig) {
            SDT_hanning(sig.data(), static_cast<int>(sig.size()));
        });

    m.def("ihaar",
        [] (arr1d& sig) {
            SDT_ihaar(sig.data(), static_cast<int>(sig.size()));
        });

    m.def("kinetic", &SDT_kinetic);
    m.def("samples_in_air", &SDT_samplesInAir);
    m.def("samples_in_air_inv", &SDT_samplesInAir_inv);
    m.def("set_samplerate", &SDT_setSampleRate);

    m.def("sinc",
        [] (arr1d& sig, double f) {
            SDT_sinc(sig.data(), f, static_cast<int>(sig.size()));
        });

    m.def("true_peak_pos",
        [] (arr1d& sig, int peak) {
            return SDT_truePeakPos(sig.data(), peak);
        });

    m.def("true_peak_value",
        [] (arr1d& sig, int peak) {
            return SDT_truePeakValue(sig.data(), peak);
        });

    m.def("wrap", &SDT_wrap);

    m.def("get_samplerate",
        [] () { return SDT_sampleRate; }
    );

    m.def("get_timestep",
        [] () { return SDT_timeStep; }
    );
}

void add_dcmotor_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("dcmotor");

    nb::class_<DCMotor>(m, "DCMotor")
        .def(nb::init<long>())
        .SDT_BIND_PROPERTY_RW(max_size, DCMotor, MaxSize, long)
        .SDT_BIND_PROPERTY_RW(rpm, DCMotor, Rpm, double)
        .SDT_BIND_PROPERTY_RW(load, DCMotor, Load, double)
        .SDT_BIND_PROPERTY_RW(coils, DCMotor, Coils, long)
        .SDT_BIND_PROPERTY_RW(size, DCMotor, Size, double)
        .SDT_BIND_PROPERTY_RW(reson, DCMotor, Reson, double)
        .SDT_BIND_PROPERTY_RW(gear_ratio, DCMotor, GearRatio, double)
        .SDT_BIND_PROPERTY_RW(harshness, DCMotor, Harshness, double)
        .SDT_BIND_PROPERTY_RW(rotor_gain, DCMotor, RotorGain, double)
        .SDT_BIND_PROPERTY_RW(gear_gain, DCMotor, GearGain, double)
        .SDT_BIND_PROPERTY_RW(brush_gain, DCMotor, BrushGain, double)
        .SDT_BIND_PROPERTY_RW(air_gain, DCMotor, AirGain, double)
        .def("update", &DCMotor::update)
        .def("dsp", &DCMotor::dsp);
}

void add_demix_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("demix");

    nb::class_<Demix>(m, "Demix")
        .def(nb::init<int, int>())
        .SDT_BIND_PROPERTY_RW(size, Demix, Size, int)
        .SDT_BIND_PROPERTY_RW(radius, Demix, Radius, int)
        .SDT_BIND_PROPERTY_RW(overlap, Demix, Overlap, double)
        .SDT_BIND_PROPERTY_RW(noise_threshold, Demix, NoiseThreshold, double)
        .SDT_BIND_PROPERTY_RW(tonal_threshold, Demix, TonalThreshold, double)
        .def("dsp", &Demix::dsp);
}

void add_effects_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("effects");

    nb::class_<PitchShift>(m, "PitchShift")
        .def(nb::init<int, int>())
        .SDT_BIND_PROPERTY_RW(size, PitchShift, Size, int)
        .SDT_BIND_PROPERTY_RW(oversample, PitchShift, Oversample, int)
        .SDT_BIND_PROPERTY_RW(ratio, PitchShift, Ratio, double)
        .SDT_BIND_PROPERTY_RW(overlap, PitchShift, Overlap, double)
        .def("dsp", &PitchShift::dsp);

    nb::class_<Reverb>(m, "Reverb")
        .def(nb::init<long>())
        .SDT_BIND_PROPERTY_RW(max_delay, Reverb, MaxDelay, long)
        .SDT_BIND_PROPERTY_RW(x_size, Reverb, XSize, double)
        .SDT_BIND_PROPERTY_RW(y_size, Reverb, YSize, double)
        .SDT_BIND_PROPERTY_RW(z_size, Reverb, ZSize, double)
        .SDT_BIND_PROPERTY_RW(randomness, Reverb, Randomness, double)
        .SDT_BIND_PROPERTY_RW(time, Reverb, Time, double)
        .SDT_BIND_PROPERTY_RW(time_1k, Reverb, Time1k, double)
        .def("update", &Reverb::update)
        .def("dsp", &Reverb::dsp);
}

void add_filters_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("filters");

    nb::class_<AllPass>(m, "AllPass")
        .def(nb::init<>())
        .def("set_feedback", &AllPass::setFeedback)
        .def("dsp", &AllPass::dsp);

    nb::class_<Average>(m, "Average")
        .def(nb::init<long>())
        .def("set_window", &Average::setWindow)
        .def("dsp", &Average::dsp);

    nb::class_<Biquad>(m, "Biquad")
        .def(nb::init<int>())
        .def("butterworth_lp", &Biquad::butterworthLP)
        .def("butterworth_hp", &Biquad::butterworthHP)
        .def("butterworth_ap", &Biquad::butterworthAP)
        .def("linkwitz_riley_lp", &Biquad::linkwitzRileyLP)
        .def("linkwitz_riley_hp", &Biquad::linkwitzRileyHP)
        .def("dsp", &Biquad::dsp);

    nb::class_<Comb>(m, "Comb")
        .def(nb::init<long, long>())
        .def_prop_ro("max_x_delay", &Comb::getMaxXDelay)
        .def_prop_ro("max_y_delay", &Comb::getMaxYDelay)
        .def("set_x_delay", &Comb::setXDelay)
        .def("set_y_delay", &Comb::setYDelay)
        .def("set_x_ydelay", &Comb::setXYDelay)
        .def("set_x_gain", &Comb::setXGain)
        .def("set_y_gain", &Comb::setYGain)
        .def("set_xy_gain", &Comb::setXYGain)
        .def("dsp", &Comb::dsp);

    nb::class_<DCFilter>(m, "DCFilter")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(feedback, DCFilter, Feedback, double)
        .SDT_BIND_PROPERTY_RW(frequency, DCFilter, Frequency, double)
        .def("dsp", &DCFilter::dsp);

    nb::class_<Delay>(m, "Delay")
        .def(nb::init<int>())
        .def_prop_ro("max_delay", &Delay::getMaxDelay)
        .SDT_BIND_PROPERTY_RW(delay, Delay, Delay, double)
        .def("clear", &Delay::clear)
        .def("dsp", &Delay::dsp);

    nb::class_<Envelope>(m, "Envelope")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(attack, Envelope, Attack, double)
        .SDT_BIND_PROPERTY_RW(release, Envelope, Release, double)
        .def("update", &Envelope::update)
        .def("dsp", &Envelope::dsp);

    nb::class_<OnePole>(m, "OnePole")
        .def(nb::init<>())
        .def("set_feedback", &OnePole::setFeedback)
        .def("lowpass", &OnePole::lowpass)
        .def("highpass", &OnePole::highpass)
        .def("dsp", &OnePole::dsp);

    nb::class_<TwoPoles>(m, "TwoPoles")
        .def(nb::init<>())
        .def("lowpass", &TwoPoles::lowpass)
        .def("highpass", &TwoPoles::highpass)
        .def("resonant", &TwoPoles::resonant)
        .def("dsp", &TwoPoles::dsp);

    nb::class_<Waveguide>(m, "Waveguide")
        .def(nb::init<int>())
        .def_prop_ro("max_delay", &Waveguide::getMaxDelay)
        .SDT_BIND_PROPERTY_RW(fwd_feedback, Waveguide, FwdFeedback, double)
        .SDT_BIND_PROPERTY_RW(rev_feedback, Waveguide, RevFeedback, double)
        .def_prop_ro("fwd_out", &Waveguide::getFwdOut)
        .def_prop_ro("rev_out", &Waveguide::getRevOut)
        .def("dsp", &Waveguide::dsp);
}

void add_gases_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("gases");

    nb::class_<Explosion>(m, "Explosion")
        .def(nb::init<long, long>())
        .SDT_BIND_PROPERTY_RW(max_scatter, Explosion, MaxScatter, double)
        .SDT_BIND_PROPERTY_RW(max_delay, Explosion, MaxDelay, double)
        .SDT_BIND_PROPERTY_RW(blast_time, Explosion, BlastTime, double)
        .SDT_BIND_PROPERTY_RW(scatter_time, Explosion, ScatterTime, double)
        .SDT_BIND_PROPERTY_RW(dispersion, Explosion, Dispersion, double)
        .SDT_BIND_PROPERTY_RW(distance, Explosion, Distance, double)
        .SDT_BIND_PROPERTY_RW(wave_speed, Explosion, WaveSpeed, double)
        .SDT_BIND_PROPERTY_RW(wind_speed, Explosion, WindSpeed, double)
        .def("trigger", &Explosion::trigger)
        .def("dsp", &Explosion::dsp);

    nb::class_<WindKarman>(m, "WindKarman")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(diameter, WindKarman, Diameter, double)
        .SDT_BIND_PROPERTY_RW(wind_speed, WindKarman, WindSpeed, double)
        .def("dsp", &WindKarman::dsp);

    nb::class_<WindFlow>(m, "WindFlow")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(wind_speed, WindFlow, WindSpeed, double)
        .def("update", &WindFlow::update)
        .def("dsp", &WindFlow::dsp);

    nb::class_<WindCavity>(m, "WindCavity")
        .def(nb::init<int>())
        .SDT_BIND_PROPERTY_RW(max_delay, WindCavity, MaxDelay, double)
        .SDT_BIND_PROPERTY_RW(length, WindCavity, Length, double)
        .SDT_BIND_PROPERTY_RW(diameter, WindCavity, Diameter, double)
        .SDT_BIND_PROPERTY_RW(wind_speed, WindCavity, WindSpeed, double)
        .def("dsp", &WindCavity::dsp);
}

void add_interactors_submodule(nb::module_& root) {
    nb::module_ m = root.def_submodule("interactors");

    nb::class_<Interactor>(m, "Interactor")
        .SDT_BIND_PROPERTY_RW(first_resonator, Interactor, FirstResonator, std::shared_ptr<Resonator>)
        .SDT_BIND_PROPERTY_RW(second_resonator, Interactor, SecondResonator, std::shared_ptr<Resonator>)
        .SDT_BIND_PROPERTY_RW(first_point, Interactor, FirstPoint, long)
        .SDT_BIND_PROPERTY_RW(second_point, Interactor, SecondPoint, long)
        .def("compute_force", &Interactor::computeForce)
        .def("dsp", &Interactor::dsp);

    nb::class_<Impact, Interactor>(m, "Impact")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(stiffness, Impact, Stiffness, double)
        .SDT_BIND_PROPERTY_RW(dissipation, Impact, Dissipation, double)
        .SDT_BIND_PROPERTY_RW(shape, Impact, Shape, double);
}

void add_liquids_submodule(nb::module_& root) {
    nb::module_ m = root.def_submodule("liquids");

    nb::class_<Bubble>(m, "Bubble")
      .def(nb::init<>())
      .SDT_BIND_PROPERTY_RW(radius, Bubble, Radius, double)
      .SDT_BIND_PROPERTY_RW(rise_factor, Bubble, RiseFactor, double)
      .SDT_BIND_PROPERTY_RW(depth, Bubble, Depth, double)
      .def("dsp", &Bubble::dsp)
      .def("norm_amp", &Bubble::normAmp)
      .def("trigger", &Bubble::trigger);

    nb::class_<FluidFlow>(m, "FluidFlow")
        .def(nb::init<int>())
        .SDT_BIND_PROPERTY_RW(n_bubbles, FluidFlow, NBubbles, int)
        .SDT_BIND_PROPERTY_RW(min_radius, FluidFlow, MinRadius, double)
        .SDT_BIND_PROPERTY_RW(max_radius, FluidFlow, MaxRadius, double)
        .SDT_BIND_PROPERTY_RW(exp_radius, FluidFlow, ExpRadius, double)
        .SDT_BIND_PROPERTY_RW(min_depth, FluidFlow, MinDepth, double)
        .SDT_BIND_PROPERTY_RW(max_depth, FluidFlow, MaxDepth, double)
        .SDT_BIND_PROPERTY_RW(exp_depth, FluidFlow, ExpDepth, double)
        .SDT_BIND_PROPERTY_RW(rise_factor, FluidFlow, RiseFactor, double)
        .SDT_BIND_PROPERTY_RW(rise_cutoff, FluidFlow, RiseCutoff, double)
        .SDT_BIND_PROPERTY_RW(avg_rate, FluidFlow, AvgRate, double)
        .def("dsp", &FluidFlow::dsp);
}

void add_motor_submodule(nb::module_& root) {
    nb::module_ m = root.def_submodule("motor");

    nb::class_<Motor>(m, "Motor")
        .def(nb::init<long>())
        .def("set_rpm", &Motor::setRpm)
        .SDT_BIND_PROPERTY_RW(max_delay, Motor, MaxDelay, long)
        .SDT_BIND_PROPERTY_RW(cycle, Motor, Cycle, double)
        .SDT_BIND_PROPERTY_RW(throttle, Motor, Throttle, double)
        .SDT_BIND_PROPERTY_RW(n_cylinders, Motor, NCylinders, int)
        .SDT_BIND_PROPERTY_RW(cylinder_size, Motor, CylinderSize, double)
        .SDT_BIND_PROPERTY_RW(compression_ratio, Motor, CompressionRatio, double)
        .SDT_BIND_PROPERTY_RW(spark_time, Motor, SparkTime, double)
        .SDT_BIND_PROPERTY_RW(asymmetry, Motor, Asymmetry, double)
        .SDT_BIND_PROPERTY_RW(backfire, Motor, Backfire, double)
        .SDT_BIND_PROPERTY_RW(intake_size, Motor, IntakeSize, double)
        .SDT_BIND_PROPERTY_RW(extractor_size, Motor, ExtractorSize, double)
        .SDT_BIND_PROPERTY_RW(exhaust_size, Motor, ExhaustSize, double)
        .SDT_BIND_PROPERTY_RW(expansion, Motor, Expansion, double)
        .SDT_BIND_PROPERTY_RW(muffler_size, Motor, MufflerSize, double)
        .SDT_BIND_PROPERTY_RW(muffler_feedback, Motor, MufflerFeedback, double)
        .SDT_BIND_PROPERTY_RW(outlet_size, Motor, OutletSize, double)
        .SDT_BIND_PROPERTY_RW(damp, Motor, Damp, double)
        .SDT_BIND_PROPERTY_RW(dc, Motor, Dc, double)
        .def("set_two_stroke", &Motor::setTwoStroke)
        .def("set_four_stroke", &Motor::setFourStroke)
        .def("update", &Motor::update)
        .def("dsp", &Motor::dsp);
}

void add_oscillators_submodule(nb::module_& root) {
    nb::module_ m = root.def_submodule("oscillators");

    nb::class_<PinkNoise>(m, "PinkNoise")
        .def(nb::init<int>())
        .def("dsp", &PinkNoise::dsp);

    m.def("white_noise", &whiteNoise);
}

void add_resonators_submodule(nb::module_& root) {
    nb::module_ m = root.def_submodule("resonators");

    nb::class_<Resonator>(m, "Resonator")
        .def(nb::init<int, int>())
        .def("get_position", &Resonator::getPosition)
        .def("set_position", &Resonator::setPosition)
        .def("get_velocity", &Resonator::getVelocity)
        .def("set_velocity", &Resonator::setVelocity)
        .def("get_frequency", &Resonator::getFrequency)
        .def("set_frequency", &Resonator::setFrequency)
        .def("get_decay", &Resonator::getDecay)
        .def("set_decay", &Resonator::setDecay)
        .def("get_weight", &Resonator::getWeight)
        .def("set_weight", &Resonator::setWeight)
        .def("get_gain", &Resonator::getGain)
        .def("set_gain", &Resonator::setGain)
        .SDT_BIND_PROPERTY_RW(n_pickups, Resonator, NPickups, int)
        .SDT_BIND_PROPERTY_RW(n_modes, Resonator, NModes, int)
        .SDT_BIND_PROPERTY_RW(active_modes, Resonator, ActiveModes, int)
        .SDT_BIND_PROPERTY_RW(fragment_size, Resonator, FragmentSize, double)
        .def("apply_force", &Resonator::applyForce)
        .def("compute_energy", &Resonator::computeEnergy)
        .def("dsp", &Resonator::dsp);
}

NB_MODULE(_pysdt_impl, m) {
    add_analysis_submodule(m);
    add_control_submodule(m);
    add_common_submodule(m);
    add_dcmotor_submodule(m);
    add_demix_submodule(m);
    add_effects_submodule(m);
    add_filters_submodule(m);
    add_gases_submodule(m);
    add_interactors_submodule(m);
    add_liquids_submodule(m);
    add_motor_submodule(m);
    add_oscillators_submodule(m);
    add_resonators_submodule(m);
}