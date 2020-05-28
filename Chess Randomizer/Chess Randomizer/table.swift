//
//  table.swift
//  Chess Randomizer
//
//  Created by Anton Marku on 5/9/20.
//  Copyright © 2020 Anton Marku. All rights reserved.
//

import UIKit
class Table: UIView {
    func place_pieces() {
        for i in items {
            let i_role = UIImage(named: i.role)
            i_role?.draw(in: CGRect(x: i.col * 39, y: i.row * 39, width: 39, height: 39))
        }
    }
    
    func makeTable() {
        makeRow(y: 0 * 39); makeRow(y: 2 * 39); makeRow(y: 4 * 39); makeRow(y: 6 * 39)
    }
    
    func makeRow(y: CGFloat) {
        makeBox(x: 1 * 39, y: y);makeBox(x: 3 * 39, y: y);makeBox(x: 5 * 39, y: y);makeBox(x: 7 * 39, y: y);makeBox(x: 0 * 39, y: y + 39);makeBox(x: 2 * 39, y: y + 39);makeBox(x: 4 * 39, y: y + 39);makeBox(x: 6 * 39, y: y + 39)
    }
    
    func makeBox(x: CGFloat, y: CGFloat) {
        let path = UIBezierPath(rect: CGRect(x: x, y: y, width: 39, height: 39))
        UIColor.lightGray.setFill()
        path.fill()
    }
    
    var items = Set<single_piece>()
    var Mover: Mover?
    var start_c = -1
    var start_r = -1
    
    override func draw(_ rect: CGRect) {
        makeTable()
        place_pieces()
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        let touch = touches.first!
        let fingerLocation = touch.location(in: self)
        start_c = Int(fingerLocation.x / 39)
        start_r = Int(fingerLocation.y / 39)
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        let touch = touches.first!
        let fingerLocation = touch.location(in: self)
        let end_c = Int(fingerLocation.x / 39)
        let end_r = Int(fingerLocation.y / 39)
        Mover?.shift_location(start_c: start_c, start_r: start_r, end_c: end_c, end_r: end_r)
    }
}
