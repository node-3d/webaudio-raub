'use strict';

const { inspect, inherits } = require('node:util');

const { AudioContext } = require('../core');
const JsBaseAudioContext = require('./base-audio-context');

inherits(AudioContext, JsBaseAudioContext);


class JsAudioContext extends AudioContext {
	constructor(opts = {}) {
		if (opts.sampleRate) {
			super(opts.sampleRate);
		} else {
			super();
		}
	}
	
	[inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'AudioContext {}';
	}
}

module.exports = JsAudioContext;
