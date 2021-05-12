'use strict';

const { AudioContext } = require('..');


describe('WebAudio', () => {
	
	let WebAudio = null;
	let context = null;
	
	it('is imported correctly', () => {
		WebAudio = require('..');
		expect(typeof WebAudio).toBe('object');
	});
	
	it('creates an AudioContext instance', () => {
		context = new AudioContext();
		expect(typeof context).toBe('object');
	});
	
	it('creates an OscillatorNode instance', () => {
		const oscillator = context.createOscillator();
		expect(typeof oscillator).toBe('object');
	});
	
});
