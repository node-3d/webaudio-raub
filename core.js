'use strict';

var SegfaultHandler = require('segfault-handler');
SegfaultHandler.registerHandler("crash.log");
console.log('SFH');

console.log('BI-L');
// Add deps dll dirs
require('deps-labsound-raub');
console.log('AI-L');
const { bin } = require('addon-tools-raub');
console.log('BI-W');
const core = require(`./${bin}/webaudio`);
console.log('AI-W');

module.exports = core;
