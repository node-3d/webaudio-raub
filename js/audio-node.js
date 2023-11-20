'use strict';

const { inspect, inherits } = require('util');
const Emitter = require('events');

const { AudioNode } = require('../core');

inherits(AudioNode, Emitter);

let nextId = 1;
const genId = () => nextId++;
const nonGcDict = {};


function JsAudioNode(ctx, node) {
	AudioNode.call(this, ctx, node);
	
	// Prevent garbage collection until node is intentionally destroyed
	this.__nonGcId = genId();
	nonGcDict[this.__nonGcId] = this;
	this.on('destroy', () => {
		delete nonGcDict[this.__nonGcId];
	});
}

JsAudioNode.prototype = {
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
		return 'AudioNode {}';
	},
};

inherits(JsAudioNode, AudioNode);

module.exports = JsAudioNode;
