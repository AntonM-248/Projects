//
//  GameView.swift
//  Chess Randomizer
//
//  Created by Anton Marku on 5/9/20.
//  Copyright © 2020 Anton Marku. All rights reserved.
//

import UIKit


class GameView: UIViewController, Mover {

    var current_match = rules()
    @IBAction func Start_match_button(_ sender: Any) {
        print("pressed")
    }
    
    @IBOutlet weak var match_table: Table!
    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = UserDefaults.standard.colorForKey(key: "myColor") ?? UIColor .white
        current_match.startMatch()
        match_table.items = current_match.items
        match_table.setNeedsDisplay()
        
        match_table.Mover = self
        update_announcement()
    }
    
    @IBOutlet weak var announcement: UILabel!
    
    @IBOutlet weak var turn: UILabel!
    func shift_location(start_c: Int, start_r: Int, end_c: Int, end_r: Int) {
        current_match.shift_location(start_c: start_c, start_r: start_r, end_c: end_c, end_r: end_r)
        match_table.items = current_match.items
        match_table.setNeedsDisplay()
        update_announcement()
    }
    
    func update_announcement(){
        announcement.text = current_match.news
        turn.text = current_match.turn
    }
}
