'use strict';

const { inspect, inherits } = require('util');
const Emitter = require('events');

const { AudioNode } = require('../core');

inherits(AudioNode, Emitter);


function JsAudioNode(ctx, node) {
	
	AudioNode.call(this, ctx, node);
	
}

JsAudioNode.prototype = {
	
	get onerror() { return this.listeners('error'); },
	set onerror(cb) { this.on('error', cb); },
	
	get onended() { return this.listeners('ended'); },
	set onended(cb) { this.on('ended', cb); },
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'AudioNode {}';
	},
	
};

inherits(JsAudioNode, AudioNode);

module.exports = JsAudioNode;
