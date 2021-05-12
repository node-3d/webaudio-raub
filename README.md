# WebAudio for Node.js

This is a part of [Node3D](https://github.com/node-3d) project.

[![NPM](https://nodei.co/npm/webaudio-raub.png?compact=true)](https://www.npmjs.com/package/webaudio-raub)
[![CodeFactor](https://www.codefactor.io/repository/github/node-3d/webaudio-raub/badge)](https://www.codefactor.io/repository/github/node-3d/webaudio-raub)

```
npm i webaudio-raub
```

**This module is WORK IN PROGRESS.**
Some features are missing for good.


## Synopsis

**Node.js** addon implementing the
[Web Audio Api](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API).

> Note: this **addon uses N-API**, and therefore is ABI-compatible across different
Node.js versions. Addon binaries are precompiled and **there is no compilation**
step during the `npm i` command.


## Usage

Simply require any class you like from the module and then follow the
[doc](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API):

```
const { AudioContext } = require('webaudio-raub'); // usually this is enough
```

Currently exported classes:
* `AudioBuffer`
* `AudioContext`
* `AudioParam`
* `AnalyserNode`
* `BiquadFilterNode`
* `ConvolverNode`
* `GainNode`
* `PannerNode`
* `AudioBufferSourceNode`
* `OscillatorNode`
* `AudioScheduledSourceNode`

In examples directory, currently working examples are prepended with `_`.
