'use strict';

const { inspect, inherits } = require('util');
const Emitter = require('events');

const { AudioListener } = require('../core');
const JsAudioParam = require('./audio-param');

inherits(AudioListener, Emitter);


function JsAudioListener(ctx, listener) {
	AudioListener.call(this, ctx, listener, JsAudioParam);
}

JsAudioListener.prototype = {
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'AudioListener {}';
	},
	
};

inherits(JsAudioListener, AudioListener);

module.exports = JsAudioListener;
