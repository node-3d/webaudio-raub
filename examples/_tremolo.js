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
	osc.type = 'triangle';
	osc.start(0);
	osc.frequency.value = 440;
	
	// Set up processing chain
	// modulator > modulatorGain ---> osc frequency
	//                                osc > context
	modulator.connect(modulatorGain);
	modulatorGain.connect(modulator.frequency);
	osc.connect(context.destination);
	
	// 30 sec
	await new Promise(res => setTimeout(res, 30000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

