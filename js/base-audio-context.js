'use strict';

const { inspect } = require('util');

const EventEmitter = require('events');

const { BaseAudioContext } = require('../core');


BaseAudioContext.prototype.__proto__ = EventEmitter.prototype;
BaseAudioContext._Super = EventEmitter.constructor;

class JsBaseAudioContext extends BaseAudioContext {
	
	constructor(ctx) {
		console.log('base-audio-context.js', '111');
		super(ctx);
		console.log('base-audio-context.js', '222');
	}
	
	get onerror() { return this.listeners('error'); }
	set onerror(cb) { this.on('error', cb); }
	
	get onstatechange() { return this.listeners('statechange'); }
	set onstatechange(cb) { this.on('statechange', cb); }
	
	[inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'BaseAudioContext {}';
	}
	
}

JsBaseAudioContext.UPDATE_INTERVAL = 20;

JsBaseAudioContext.startUpdater = that => {
	that._updateTimerId = setInterval(() => that.update(), JsBaseAudioContext.UPDATE_INTERVAL);
	that._updateTimerId.unref();
};

JsBaseAudioContext.stopUpdater = that => {
	// console.log('\n\nSTOP UPDATER\n\n');
	clearInterval(that._updateTimerId);
	that._updateTimerId = null;
};


module.exports = JsBaseAudioContext;
