# WebAudio for Node.js

This is a part of [Node3D](https://github.com/node-3d) project.

[![NPM](https://badge.fury.io/js/webaudio-raub.svg)](https://badge.fury.io/js/webaudio-raub)
[![ESLint](https://github.com/node-3d/webaudio-raub/actions/workflows/eslint.yml/badge.svg)](https://github.com/node-3d/webaudio-raub/actions/workflows/eslint.yml)
[![Test](https://github.com/node-3d/webaudio-raub/actions/workflows/test.yml/badge.svg)](https://github.com/node-3d/webaudio-raub/actions/workflows/test.yml)
[![Cpplint](https://github.com/node-3d/webaudio-raub/actions/workflows/cpplint.yml/badge.svg)](https://github.com/node-3d/webaudio-raub/actions/workflows/cpplint.yml)

```console
npm i -s webaudio-raub
```

**This module is WORK IN PROGRESS.**
Some features are missing for good.


**Node.js** addon implementing the
[Web Audio Api](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API).

> Note: this **addon uses N-API**, and therefore is ABI-compatible across different
Node.js versions. Addon binaries are precompiled and **there is no compilation**
step during the `npm i` command.


Simply require any class you like from the module and then follow the
[doc](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API):

```js
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
