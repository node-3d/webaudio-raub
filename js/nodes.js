'use strict';

const { inspect, inherits } = require('util');

const core = require('../core');
const JsAudioNode = require('./audio-node');
const JsAudioParam = require('./audio-param');
const JsAudioScheduledSourceNode = require('./audio-scheduled-source-node');


const baseDescs = [
	'AnalyserNode',
	'BiquadFilterNode',
	// 'ChannelMergerNode',
	// 'ChannelSplitterNode',
	'ConvolverNode',
	'DelayNode',
	// 'DynamicsCompressorNode',
	'GainNode',
	// 'IIRFilterNode',
	'PannerNode',
	// 'PeriodicWaveNode',
	// 'ScriptProcessorNode',
	// 'StereoPannerNode',
	// 'WaveShaperNode',
];

const scheduledDescs = [
	'AudioBufferSourceNode', 'OscillatorNode',
];

const subclassBase = (name, SuperNode) => {
	const SuperClass = core[name];
	inherits(SuperClass, SuperNode);
	
	class JsNode extends SuperClass {
		constructor(ctx, opts = {}) {
			super(ctx, JsAudioParam, opts);
			this._opts = opts;
		}
		
		[inspect.custom]() { return this.toString(); }
		
		toString() {
			return `${name} ${JSON.stringify(this._opts, null, '\t')}`;
		}
	}
	
	return JsNode;
};


const baseNodes = {
	...baseDescs.reduce(
		(e, name) => {
			e[name] = subclassBase(name, JsAudioNode);
			return e;
		},
		{},
	),
	AudioScheduledSourceNode: JsAudioScheduledSourceNode,
};

const scheduledNodes = scheduledDescs.reduce(
	(e, name) => {
		e[name] = subclassBase(name, JsAudioScheduledSourceNode);
		return e;
	},
	{},
);


module.exports = {
	...baseNodes,
	...scheduledNodes,
};
