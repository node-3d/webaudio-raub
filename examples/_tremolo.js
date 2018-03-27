'use strict';

const { AudioContext } = require('..');


(async () => { try {
	
	const context = new AudioContext();
	
	const modulator = context.createOscillator();
	modulator.type = 'sine';
	modulator.start(0);
	modulator.frequency.value = 8;
	
	const modulatorGain = context.createGain();
	modulatorGain.gain.value = 10;
	
	const osc = context.createOscillator();
	modulator.type = 'triangle';
	modulator.start(0);
	modulator.frequency.value = 440;
	
	modulator.connect(modulatorGain);
	modulatorGain.connect(modulator.frequency);
	osc.connect(context.destination);
	
	// 5 sec
	await new Promise(res => setTimeout(res, 5000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

