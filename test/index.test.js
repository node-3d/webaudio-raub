'use strict';

const assert = require('node:assert').strict;
const { describe, it } = require('node:test');

const WebAudio = require('..');
const { AudioContext } = WebAudio;


describe('WebAudio', () => {
	const context = new AudioContext();
	
	it('creates an AudioContext instance', () => {
		assert.ok(context instanceof AudioContext);
	});
	
	it('creates an OscillatorNode instance', () => {
		const oscillator = context.createOscillator();
		assert.strictEqual(typeof oscillator, 'object');
	});
});
