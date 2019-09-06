'use strict';

const { inspect, inherits } = require('util');
const Emitter = require('events');

const { BaseAudioContext } = require('../core');
const JsAudioDestinationNode = require('./audio-destination-node');
const JsAudioListener = require('./audio-listener');


inherits(BaseAudioContext, Emitter);


function JsBaseAudioContext(ctx) {
	
	BaseAudioContext.call(this, ctx);
	
	this._initListener(JsAudioDestinationNode, JsAudioListener);
	
	this._updateTimerId = setInterval(
		() => this.update(),
		JsBaseAudioContext.UPDATE_INTERVAL
	);
	this._updateTimerId.unref();
	
}

JsBaseAudioContext.UPDATE_INTERVAL = 20;

JsBaseAudioContext.prototype = {
	
	get onerror() { return this.listeners('error'); },
	set onerror(cb) { this.on('error', cb); },
	
	get onstatechange() { return this.listeners('statechange'); },
	set onstatechange(cb) { this.on('statechange', cb); },
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'BaseAudioContext {}';
	},
	
	stopUpdater() {
		console.log('\n\nSTOP UPDATER\n\n');
		clearInterval(this._updateTimerId);
		this._updateTimerId = null;
	},
	
};

inherits(JsBaseAudioContext, BaseAudioContext);

module.exports = JsBaseAudioContext;
