'use strict';

const { inspect, inherits } = require('util');

const core = require('../core');
const JsAudioNode = require('./audio-node');
const JsAudioParam = require('./audio-param');


const descriptions = [
	{ name: 'AnalyserNode', optset: [] },
	{ name: 'BiquadFilterNode', optset: [] },
	{ name: 'AudioBufferSourceNode', optset: [] },
	// { name: 'ChannelMergerNode', optset: [] },
	// { name: 'ChannelSplitterNode', optset: [] },
	// { name: 'ConstantSourceNode', optset: [] },
	{ name: 'ConvolverNode', optset: [] },
	{ name: 'DelayNode', optset: [] },
	// { name: 'DynamicsCompressorNode', optset: [] },
	{ name: 'GainNode', optset: [] },
	// { name: 'IIRFilterNode', optset: [] },
	{ name: 'OscillatorNode', optset: [] },
	{ name: 'PannerNode', optset: [] },
	// { name: 'PeriodicWaveNode', optset: [] },
	// { name: 'ScriptProcessorNode', optset: [] },
	// { name: 'StereoPannerNode', optset: [] },
	// { name: 'WaveShaperNode', optset: [] },
];

const subclassNode = (name, optset) => {
	
	const SuperClass = core[name];
	inherits(SuperClass, JsAudioNode);
	
	function JsNode(ctx, opts = {}) {
		console.log('NOW CALL', SuperClass, this, ctx, JsAudioParam);
		SuperClass.call(this, ctx, JsAudioParam);
		optset.forEach(opt => {
			if (opts[opt] !== undefined) {
				this[opt] = opts[opt];
			}
		});
	}
	
	JsNode.prototype = {
		
		[inspect.custom]() { return this.toString(); },
		
		toString() {
			return `${name} {${
				optset.length
					? ` ${optset.map(opt => `${opt}: ${this[opt]}`).join(', ')} `
					: ''
			}}`;
		},
		
	};
	
	inherits(JsNode, SuperClass);
	
	return JsNode;
	
};


module.exports = descriptions.reduce(
	(e, { name, optset }) => {
		e[name] = subclassNode(name, optset);
		return e;
	},
	{}
);
