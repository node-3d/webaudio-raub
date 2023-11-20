'use strict';

const { inspect, inherits } = require('node:util');
const Emitter = require('node:events');

const { AudioBuffer } = require('../core');

inherits(AudioBuffer, Emitter);


class JsAudioBuffer extends AudioBuffer {
	constructor(ctx, bus) {
		super(ctx, bus);
	}
	
	[inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'AudioBuffer {}';
	}
}

module.exports = JsAudioBuffer;
