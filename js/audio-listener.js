'use strict';

const { inspect, inherits } = require('node:util');
const Emitter = require('node:events');

const { AudioListener } = require('../core');
const JsAudioParam = require('./audio-param');

inherits(AudioListener, Emitter);


class JsAudioListener extends AudioListener {
	constructor(ctx, listener) {
		super(ctx, listener, JsAudioParam);
	}
	
	[inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'AudioListener {}';
	}
}

module.exports = JsAudioListener;
