'use strict';

const { inspect } = require('util');

const { AudioDestinationNode } = require('../core');
const AudioNode = require('./audio-node');


AudioDestinationNode.prototype.__proto__ = AudioNode.prototype;
AudioDestinationNode._Super = AudioNode.constructor;


class JsAudioDestinationNode extends AudioDestinationNode {
	
	constructor(ctx, _opts = {}) {
		
		const opts = {
			fftSize : 2048,
			maxDecibels : -30,
			minDecibels : -100,
			smoothingTimeConstant : 0.8,
			..._opts,
		};
		
		super(ctx);
		
		this.fftSize = opts.fftSize;
		this.maxDecibels = opts.maxDecibels;
		this.minDecibels = opts.minDecibels;
		this.smoothingTimeConstant = opts.smoothingTimeConstant;
		
	}
	
	
	[util.inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'AudioDestinationNode {}';
	}
	
}

module.exports = JsAudioDestinationNode;
