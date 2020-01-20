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
	set onerror(cb) {
		if (cb) {
			this.on('error', cb);
		} else {
			this.removeAllListeners('error');
		}
	},
	
	get onended() { return this.listeners('ended'); },
	set onended(cb) {
		if (cb) {
			this.on('ended', cb);
		} else {
			this.removeAllListeners('ended');
		}
	},
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return `AudioParam { ${this.value} }`;
	},
	
};

inherits(JsAudioParam, AudioParam);

module.exports = JsAudioParam;
