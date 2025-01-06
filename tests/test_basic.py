import pysdt

def test_samplerate():
    sr = 44100
    pysdt.common.set_samplerate(sr)
    assert pysdt.common.get_samplerate() == sr
