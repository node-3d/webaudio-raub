'use strict';

const { inspect, inherits } = require('util');
const Emitter = require('events');

const { AudioParam } = require('../core');

inherits(AudioParam, Emitter);


function JsAudioParam(ctx, param) {
	AudioParam.call(this, ctx, param);
}

JsAudioParam.prototype = {
	
	get onerror() { return this.listeners('error'); },
	set onerror(cb) { this.on('error', cb); },
	
	get onended() { return this.listeners('ended'); },
	set onended(cb) { this.on('ended', cb); },
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'AudioParam {}';
	},
	
};

inherits(JsAudioParam, AudioParam);

module.exports = JsAudioParam;
