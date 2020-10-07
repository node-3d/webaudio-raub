'use strict';

const { expect } = require('chai');

const { AudioContext } = require('..');


describe('WebAudio', () => {
	
	let WebAudio = null;
	let context = null;
	
	it('is imported correctly', () => {
		WebAudio = require('..');
		expect(WebAudio).to.be.an('object');
	});
	
	it('creates an AudioContext instance', () => {
		context = new AudioContext();
		expect(context).to.be.an('object');
	});
	
	it('creates an OscillatorNode instance', () => {
		const oscillator = context.createOscillator();
		expect(oscillator).to.be.an('object');
	});
	
});
