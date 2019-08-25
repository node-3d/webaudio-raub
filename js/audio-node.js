'use strict';

const { inspect } = require('util');
const EventEmitter = require('events');

const { AudioNode } = require('../core');


AudioNode.prototype.__proto__ = EventEmitter.prototype;

class JsAudioNode extends AudioNode {
	
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
	
	
	get onended() { return this.listeners('ended'); }
	set onended(cb) { this.on('ended', cb); }
	
	
	[inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'AudioListener {}';
	}
	
}


module.exports = JsAudioNode;
