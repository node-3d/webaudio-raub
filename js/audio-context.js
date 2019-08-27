'use strict';

const { inspect } = require('util');

const { AudioContext } = require('../core');
const JsBaseAudioContext = require('./base-audio-context');


Object.setPrototypeOf(AudioContext.prototype, JsBaseAudioContext.prototype);
Object.setPrototypeOf(AudioContext, JsBaseAudioContext);
// AudioContext.prototype.__proto__ = JsBaseAudioContext.prototype;
// AudioContext._Super = JsBaseAudioContext.prototype.constructor;


class JsAudioContext extends AudioContext {
	
	constructor(opts = {}) {
		
		if (opts.sampleRate) {
			super(opts.sampleRate);
		} else {
			console.log('audio-context.js', 'cs1', JsBaseAudioContext.constructor);
			super();
			console.log('audio-context.js', 'cs2');
		}
		
	}
	
	
	[inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'AudioContext {}';
	}
	
}

module.exports = JsAudioContext;
