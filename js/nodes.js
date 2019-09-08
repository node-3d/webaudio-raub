'use strict';

const { inspect, inherits } = require('util');

const core = require('../core');
const JsAudioNode = require('./audio-node');
const JsAudioParam = require('./audio-param');
const JsAudioScheduledSourceNode = require('./audio-scheduled-source-node');


const baseDescs = [
	{ name: 'AnalyserNode', optset: [] },
	{ name: 'BiquadFilterNode', optset: [] },
	// { name: 'ChannelMergerNode', optset: [] },
	// { name: 'ChannelSplitterNode', optset: [] },
	{ name: 'ConvolverNode', optset: [] },
	{ name: 'DelayNode', optset: [] },
	// { name: 'DynamicsCompressorNode', optset: [] },
	{ name: 'GainNode', optset: [] },
	// { name: 'IIRFilterNode', optset: [] },
	{ name: 'PannerNode', optset: [] },
	// { name: 'PeriodicWaveNode', optset: [] },
	// { name: 'ScriptProcessorNode', optset: [] },
	// { name: 'StereoPannerNode', optset: [] },
	// { name: 'WaveShaperNode', optset: [] },
];

const scheduledDescs = [
	{ name: 'AudioBufferSourceNode', optset: [] },
	// { name: 'ConstantSourceNode', optset: [] },
	{ name: 'OscillatorNode', optset: [] },
];

const subclassBase = (name, optset, SuperNode) => {
	
	const SuperClass = core[name];
	console.log('NOW CALL 11', name, SuperClass, SuperNode);
	inherits(SuperClass, SuperNode);
	
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


const baseNodes = {
	...baseDescs.reduce(
		(e, { name, optset }) => {
			e[name] = subclassBase(name, optset, JsAudioNode);
			return e;
		},
		{}
	),
	AudioScheduledSourceNode: JsAudioScheduledSourceNode,
};
console.log('BN', baseNodes, baseNodes.AudioScheduledSourceNode);
const scheduledNodes = scheduledDescs.reduce(
	(e, { name, optset }) => {
		e[name] = subclassBase(name, optset, baseNodes.AudioScheduledSourceNode);
		return e;
	},
	{}
);


module.exports = {
	...baseNodes,
	...scheduledNodes,
};
