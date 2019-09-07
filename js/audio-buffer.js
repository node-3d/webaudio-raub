'use strict';

const { inspect, inherits } = require('util');
const Emitter = require('events');

const { AudioBuffer } = require('../core');

inherits(AudioBuffer, Emitter);


function JsAudioBuffer(ctx, bus) {
	console.log('call JsAudioBuffer()', ctx, bus);
	AudioBuffer.call(this, ctx, bus);
	
}

JsAudioBuffer.prototype = {
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'AudioBuffer {}';
	},
	
};

inherits(JsAudioBuffer, AudioBuffer);

module.exports = JsAudioBuffer;
