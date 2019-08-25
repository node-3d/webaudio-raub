'use strict';

const { inspect } = require('util');

const { ConvolverNode } = require('../core');
const AudioNode = require('./audio-node');


ConvolverNode.prototype.__proto__ = AudioNode.prototype;
ConvolverNode._Super = AudioNode.constructor;


class JsConvolverNode extends ConvolverNode {
	
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
		return 'ConvolverNode {}';
	}
	
}

module.exports = JsConvolverNode;
