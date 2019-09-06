'use strict';

// Add deps dll dirs
require('deps-labsound-raub');

const { bin } = require('addon-tools-raub');

const core = require(`./${bin}/webaudio`);
var SegfaultHandler = require('segfault-handler');
 
SegfaultHandler.registerHandler("crash.log");
console.log('SFH');
module.exports = core;
