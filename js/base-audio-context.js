'use strict';

const { inspect, inherits } = require('node:util');
const Emitter = require('node:events');
const { hrtf } = require('deps-labsound-raub');

const { BaseAudioContext } = require('../core');
const JsAudioDestinationNode = require('./audio-destination-node');
const JsAudioBuffer = require('./audio-buffer');
const JsAudioListener = require('./audio-listener');
const nodes = require('./nodes');

inherits(BaseAudioContext, Emitter);
BaseAudioContext.hrtf = hrtf;


function JsBaseAudioContext(ctx, sampleRate = -1) {
	BaseAudioContext.call(this, ctx, sampleRate);
	this._initListener(JsAudioDestinationNode, JsAudioListener, sampleRate);
}

JsBaseAudioContext.prototype = {
	get onerror() { return this.listeners('error'); },
	set onerror(cb) {
		if (cb) {
			this.on('error', cb);
		} else {
			this.removeAllListeners('error');
		}
	},
	
	get onstatechange() { return this.listeners('statechange'); },
	set onstatechange(cb) {
		if (cb) {
			this.on('statechange', cb);
		} else {
			this.removeAllListeners('statechange');
		}
	},
	
	[inspect.custom]() { return this.toString(); },
	
	toString() {
		return 'BaseAudioContext {}';
	},
	
	decodeAudioData(audioData, successCallback) {
		BaseAudioContext.prototype.decodeAudioData.call(
			this,
			audioData,
			successCallback,
			JsAudioBuffer,
		);
	},
	
	createAnalyser(opts) {
		return new nodes.AnalyserNode(this, opts);
	},
	
	createBiquadFilter(opts) {
		return new nodes.BiquadFilterNode(this, opts);
	},
	
	createBuffer(opts) {
		return new JsAudioBuffer(this, opts);
	},
	
	createBufferSource(opts) {
		return new nodes.AudioBufferSourceNode(this, opts);
	},
	
	createChannelMerger(opts) {
		return new nodes.ChannelMergerNode(this, opts);
	},
	
	createChannelSplitter(opts) {
		return new nodes.ChannelSplitterNode(this, opts);
	},
	
	createConstantSource(opts) {
		return new nodes.ConstantSourceNode(this, opts);
	},
	
	createConvolver(opts) {
		return new nodes.ConvolverNode(this, opts);
	},
	
	createDelay(maxDelayTime = 1) {
		return new nodes.DelayNode(this, { maxDelayTime });
	},
	
	createDynamicsCompressor(opts) {
		return new nodes.DynamicsCompressorNode(this, opts);
	},
	
	createGain(opts) {
		return new nodes.GainNode(this, opts);
	},
	
	createIIRFilter(opts) {
		return new nodes.IIRFilterNode(this, opts);
	},
	
	createOscillator(opts) {
		return new nodes.OscillatorNode(this, opts);
	},
	
	createPanner(opts) {
		return new nodes.PannerNode(this, opts);
	},
	
	createPeriodicWave(opts) {
		return new nodes.PeriodicWaveNode(this, opts);
	},
	
	createScriptProcessor(opts) {
		return new nodes.ScriptProcessorNode(this, opts);
	},
	
	createStereoPanner(opts) {
		return new nodes.StereoPannerNode(this, opts);
	},
	
	createWaveShaper(opts) {
		return new nodes.WaveShaperNode(this, opts);
	},
};

inherits(JsBaseAudioContext, BaseAudioContext);

module.exports = JsBaseAudioContext;
