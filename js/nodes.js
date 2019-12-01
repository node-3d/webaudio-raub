'use strict';

const { inspect, inherits } = require('util');

const { hrtf } = require('deps-labsound-raub');

const core = require('../core');
const JsAudioNode = require('./audio-node');
const JsAudioParam = require('./audio-param');
const JsAudioScheduledSourceNode = require('./audio-scheduled-source-node');


const baseDescs = [
	{ name: 'AnalyserNode', paramList: [] },
	{ name: 'BiquadFilterNode', paramList: [] },
	// { name: 'ChannelMergerNode', paramList: [] },
	// { name: 'ChannelSplitterNode', paramList: [] },
	{ name: 'ConvolverNode', paramList: [] },
	{
		name: 'DelayNode',
		paramList: ['delayTime'],
		construct: (that, ctx, opts) => core.DelayNode.call(
			that,
			ctx,
			JsAudioParam,
			opts.maxDelayTime || 1
		),
	},
	// { name: 'DynamicsCompressorNode', paramList: [] },
	{ name: 'GainNode', paramList: [] },
	// { name: 'IIRFilterNode', paramList: [] },
	{ name: 'PannerNode', paramList: [] },
	// { name: 'PeriodicWaveNode', paramList: [] },
	// { name: 'ScriptProcessorNode', paramList: [] },
	// { name: 'StereoPannerNode', paramList: [] },
	// { name: 'WaveShaperNode', paramList: [] },
];

const scheduledDescs = [
	{ name: 'AudioBufferSourceNode', paramList: [] },
	// { name: 'ConstantSourceNode', paramList: [] },
	{ name: 'OscillatorNode', paramList: [] },
];

core.PannerNode.hrtf = hrtf;

const subclassBase = ({ name, paramList, construct }, SuperNode,) => {
	
	const SuperClass = core[name];
	
	inherits(SuperClass, SuperNode);
	
	function JsNode(ctx, opts = {}) {
		
		if (construct) {
			construct(this, ctx, opts);
		} else {
			SuperClass.call(this, ctx, JsAudioParam);
		}
		
		paramList.forEach(opt => {
			if (opts[opt] !== undefined) {
				this[opt].value = opts[opt];
			}
		});
		
	}
	
	JsNode.prototype = {
		
		[inspect.custom]() { return this.toString(); },
		
		toString() {
			return `${name} {${
				paramList.length
					? ` ${paramList.map(opt => `${opt}: ${this[opt]}`).join(', ')} `
					: ''
			}}`;
		},
		
	};
	
	inherits(JsNode, SuperClass);
	
	return JsNode;
	
};


const baseNodes = {
	...baseDescs.reduce(
		(e, desc) => {
			e[desc.name] = subclassBase(desc, JsAudioNode);
			return e;
		},
		{}
	),
	AudioScheduledSourceNode: JsAudioScheduledSourceNode,
};

const scheduledNodes = scheduledDescs.reduce(
	(e, desc) => {
		e[desc.name] = subclassBase(desc, baseNodes.AudioScheduledSourceNode);
		return e;
	},
	{}
);


module.exports = {
	...baseNodes,
	...scheduledNodes,
};
