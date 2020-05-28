//
//  mover.swift
//  Chess Randomizer
//
//  Created by Anton Marku on 5/9/20.
//  Copyright © 2020 Anton Marku. All rights reserved.
//

import Foundation

protocol Mover {
  func shift_location(start_c: Int, start_r: Int,
                      end_c: Int, end_r: Int)
}
