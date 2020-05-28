//
//  ViewController.swift
//  Chess Randomizer
//
//  Created by Anton Marku on 5/9/20.
//  Copyright © 2020 Anton Marku. All rights reserved.
//

import UIKit

import AudioToolbox

class ViewController: UIViewController {

    @IBOutlet weak var king_img: UIImageView!
    @IBAction func Start_match(_ sender: Any) {
        jingle.play()
    }
    private func rotateView(targetView: UIView, duration: Double = 1.0) {
        UIView.animate(withDuration: duration, delay: 0.0, options: .curveLinear, animations: {
            targetView.transform = targetView.transform.rotated(by: .pi)
        }) { finished in
            self.rotateView(targetView: targetView, duration: duration)
        }
    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        rotateView(targetView: king_img)
        jingle.play()
    }
    
    
}
let jingle = soundplayer(song: "Sound.caf")
let knock = soundplayer(song: "knock.caf")
class soundplayer{
    let song: String
    var soundID: SystemSoundID = 0
    func play(){
        AudioServicesPlaySystemSound(soundID)
    }
    init(song:String){
        self.song = song
         if let path = Bundle.main.path(forResource: song,
         ofType: nil) {
             let fileURL = URL(fileURLWithPath: path, isDirectory: false)
             let error = AudioServicesCreateSystemSoundID(fileURL as CFURL, &soundID)
             if error != kAudioServicesNoError {
                print("Error code \(error) loading sound: \(path)")
             }
         }
        
    }
}




