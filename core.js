'use strict';

const SegfaultHandler = require('segfault-handler');
SegfaultHandler.registerHandler('crash.log');

// Add deps dll dirs
require('deps-labsound-raub');
const { bin } = require('addon-tools-raub');

const core = require(`./${bin}/webaudio`);

module.exports = core;
