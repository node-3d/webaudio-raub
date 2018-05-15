'use strict';

const { AudioContext } = require('..');

const read = require('./utils/read');


(async () => { try {
	
	const context = new AudioContext();
	
	const clip = await read(`${__dirname}/samples/trainrolling.wav`);
	
	const musicClip = await new Promise(res => context.decodeAudioData(clip, b => res(b)));
	
	const oscillator = context.createOscillator();
	
	const gain = context.createGain();
	gain.gain.value = 0.0625;
	
	const musicClipNode = context.createBufferSource();
	
	musicClipNode.on('ended', () => { console.log('.on("ended"): Track "trainrolling.wav" ended.'); });
	musicClipNode.onended = () => { console.log('.onended: Track "trainrolling.wav" ended.'); };
	
	musicClipNode.on('ended', () => { setTimeout(() => musicClipNode.start(0), 100) });
	
	musicClipNode.buffer = musicClip;
	musicClipNode.connect(gain);
	musicClipNode.start(0);
	
	// osc -> gain -> destination
	oscillator.connect(gain);
	gain.connect(context.destination);
	
	oscillator.frequency.value = 440;
	oscillator.type = 'sine';
	oscillator.start(0);
	
	// 60 sec
	await new Promise(res => setTimeout(res, 600000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

