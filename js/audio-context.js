'use strict';

const { inspect } = require('util');

const { AudioContext } = require('../core');
const BaseAudioContext = require('./base-audio-context');


AudioContext.prototype.__proto__ = BaseAudioContext.prototype;
AudioContext._Super = BaseAudioContext.constructor;


class JsAudioContext extends AudioContext {
	
	constructor(opts = {}) {
		
		if (opts.sampleRate) {
			super(opts.sampleRate);
		} else {
			super();
		}
		
	}
	
	
	[util.inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'AudioContext {}';
	}
	
}

module.exports = JsAudioContext;
