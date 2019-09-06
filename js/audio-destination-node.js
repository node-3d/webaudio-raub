'use strict';

const { inspect, inherits } = require('util');

const { AudioDestinationNode } = require('../core');
const JsAudioNode = require('./audio-node');


inherits(AudioDestinationNode, JsAudioNode);


function JsAudioDestinationNode(ctx, node) {
	console.log('call JsAudioDestinationNode()', ctx, node);
	AudioDestinationNode.call(this, ctx, node);
}

JsAudioDestinationNode.prototype = {
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'AudioDestinationNode {}';
	},
	
};

inherits(JsAudioDestinationNode, AudioDestinationNode);

module.exports = JsAudioDestinationNode;
