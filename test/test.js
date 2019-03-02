'use strict';

const { expect } = require('chai');

const WebAudio = require('webaudio-raub');



describe('WebAudio', () => {
	
	it('exports an object', () => {
		expect(WebAudio).to.be.an('object');
	});
	
});
