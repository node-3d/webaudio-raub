'use strict';

const { inspect } = require('util');

const { hrtf } = require('deps-labsound-raub');

const { PannerNode } = require('../core');
const AudioNode = require('./audio-node');


PannerNode.prototype.__proto__ = AudioNode.prototype;
PannerNode._Super = AudioNode.constructor;


class JsPannerNode extends PannerNode {
	
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
		return 'PannerNode {}';
	}
	
}

PannerNode.hrtf = hrtf;

module.exports = JsPannerNode;
