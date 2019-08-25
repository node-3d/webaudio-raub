'use strict';

const { inspect } = require('util');

const { OscillatorNode } = require('../core');
const AudioNode = require('./audio-node');


OscillatorNode.prototype.__proto__ = AudioNode.prototype;
OscillatorNode._Super = AudioNode.constructor;


class JsOscillatorNode extends OscillatorNode {
	
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
	
	
	[inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'OscillatorNode {}';
	}
	
}

module.exports = JsOscillatorNode;
