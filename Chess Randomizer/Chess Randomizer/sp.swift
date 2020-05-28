//
//  sp.swift
//  Chess Randomizer
//
//  Created by Anton Marku on 5/9/20.
//  Copyright © 2020 Anton Marku. All rights reserved.
//

import Foundation
struct single_piece: Hashable {
    let col: Int
    let row: Int
    let team: String
    let role: String
    var moved: Bool
}
