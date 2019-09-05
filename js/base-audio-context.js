'use strict';

const { inspect, inherits } = require('util');
const Emitter = require('events');

const { BaseAudioContext } = require('../core');

console.log('BC', BaseAudioContext, Emitter);
inherits(BaseAudioContext, Emitter);


function JsBaseAudioContext(ctx) {
	console.log('base-audio-context.js', 'cs1', this, ctx);
	BaseAudioContext.call(this, ctx);
	console.log('base-audio-context.js', 'cs2');
}
inherits(JsBaseAudioContext, BaseAudioContext);


JsBaseAudioContext.prototype = {
	
	get onerror() { return this.listeners('error'); },
	set onerror(cb) { this.on('error', cb); },
	
	get onstatechange() { return this.listeners('statechange'); },
	set onstatechange(cb) { this.on('statechange', cb); },
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'BaseAudioContext {}';
	},
	
};


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
