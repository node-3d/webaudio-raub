'use strict';

const { inspect } = require('util');

const { AnalyserNode } = require('../core');
const AudioNode = require('./audio-node');


AnalyserNode.prototype.__proto__ = AudioNode.prototype;

class JsAnalyserNode extends AnalyserNode {
	
	constructor(ctx, _opts = {}) {
		
		const opts = {
			fftSize : 2048,
			maxDecibels : -30,
			minDecibels : -100,
			smoothingTimeConstant : 0.8,
			..._opts,
		};
		
		super(ctx);
		
	}
	
	
	[inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'AnalyserNode {}';
	}
	
}


module.exports = JsAnalyserNode;
