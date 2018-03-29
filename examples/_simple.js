'use strict';

const fs = require('fs');

const { AudioContext } = require('..');


(async () => { try {
	
	const context = new AudioContext();
	
	const clip = await new Promise((res, rej) => fs.readFile(
		`${__dirname}/samples/voice.ogg`,
		(err, data) => err ? rej(err) : res(data)
	));
	
	const musicClip = await new Promise(res => context.decodeAudioData(clip, b => res(b)));
	
	const oscillator = context.createOscillator();
	
	const gain = context.createGain();
	gain.gain.value = 0.0625;
	
	const musicClipNode = context.createBufferSource();
	musicClipNode.buffer = musicClip;
	musicClipNode.connect(gain);
	musicClipNode.start(0);
	
	// osc -> gain -> destination
	oscillator.connect(gain);
	gain.connect(context.destination);
		
	oscillator.frequency.value = 440;
	oscillator.type = 'sine';
	oscillator.start(0);
	
	// 4 sec
	await new Promise(res => setTimeout(res, 4000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

