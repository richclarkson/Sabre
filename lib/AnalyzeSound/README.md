# AnalyzeSound
Author: Richard Clarkson
Date: 2018.02.02
Version: 1.0

## Description
This library provides a FFT or RMS analysis of sound readings generated using the Teensy Audio Library

## Usage
1. `analyzeFFT()` uses Fast Fouriay Transform to ansylise sound readings and return int from 0-155 of only the specified channel
2. `analyzeLevel()` uses RMS to ansylise sound readings and returns an int from 0-115
3. `analyzeFFTall();` uses Fast Fouriay Transform to ansylise sound readings and return an array of all 8 int values from 0-115