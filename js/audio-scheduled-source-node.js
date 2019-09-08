'use strict';

const { inspect, inherits } = require('util');

const { AudioScheduledSourceNode } = require('../core');
const JsAudioNode = require('./audio-node');


inherits(AudioScheduledSourceNode, JsAudioNode);


function JsAudioScheduledSourceNode(ctx, node) {
	console.log('call JsAudioScheduledSourceNode()', ctx, node);
	AudioScheduledSourceNode.call(this, ctx, node);
}

JsAudioScheduledSourceNode.prototype = {
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'AudioScheduledSourceNode {}';
	},
	
};

inherits(JsAudioScheduledSourceNode, AudioScheduledSourceNode);

module.exports = JsAudioScheduledSourceNode;
