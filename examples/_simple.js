'use strict';

const { AudioContext } = require('..');

const read = require('./utils/read');


(async () => { try {
	
	const context = new AudioContext();
	console.log('0');
	const clip = await read(`${__dirname}/samples/trainrolling.wav`);
	console.log('_simple.js', context.decodeAudioData);
	const musicClip = await new Promise(res => context.decodeAudioData(clip, b => res(b)));
	console.log('1');
	const oscillator = context.createOscillator();
	console.log('2');
	const gain = context.createGain();
	gain.gain.value = 0.0625;
	console.log('3');
	const musicClipNode = context.createBufferSource();
	console.log('4');
	musicClipNode.on('ended', () => { console.log('.on("ended"): Track "trainrolling.wav" ended.'); });
	musicClipNode.onended = () => { console.log('.onended: Track "trainrolling.wav" ended.'); };
	console.log('5');
	musicClipNode.on('ended', () => { setTimeout(() => musicClipNode.start(0), 100) });
	console.log('6');
	musicClipNode.buffer = musicClip;
	console.log('61');
	musicClipNode.connect(gain);
	console.log('62');
	musicClipNode.start(0);
	console.log('7');
	// osc -> gain -> destination
	oscillator.connect(gain);
	gain.connect(context.destination);
	
	oscillator.frequency.value = 440;
	oscillator.type = 'sine';
	oscillator.start(0);
	
	// 60 sec
	await new Promise(res => setTimeout(res, 6000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();
