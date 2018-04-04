# waa

Web Audio Api implementation for Node.js


## Install

```
npm i -s waa-raub
```

Note: as this is a compiled addon, compilation tools must be in place on your system.
Such as MSVS13 for Windows, where **ADMIN PRIVELEGED**
`npm i -g windows-build-tools` most probably helps.


## Usage

This module is trying to comply with the documented
[Web Audio Api](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API).

Simply require any class you like from the module and then follow the doc:

```
const { AudioContext } = require('waa-raub'); // usually this is enough
```
