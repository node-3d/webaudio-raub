'use strict';

const { inspect, inherits } = require('node:util');
const Emitter = require('node:events');

const { AudioParam } = require('../core');

inherits(AudioParam, Emitter);


class JsAudioParam extends AudioParam {
	constructor(ctx, param) {
		super(ctx, param);
	}
	
	get onerror() { return this.listeners('error'); }
	set onerror(cb) {
		if (cb) {
			this.on('error', cb);
		} else {
			this.removeAllListeners('error');
		}
	}
	
	get onended() { return this.listeners('ended'); }
	set onended(cb) {
		if (cb) {
			this.on('ended', cb);
		} else {
			this.removeAllListeners('ended');
		}
	}
	
	[inspect.custom]() { return this.toString(); }
	
	toString() {
		return `AudioParam { ${this.value} }`;
	}
}

module.exports = JsAudioParam;
