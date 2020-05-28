//
//  SettingVC.swift
//  Chess Randomizer
//
//  Created by Anton Marku on 5/12/20.
//  Copyright © 2020 Anton Marku. All rights reserved.
//

import UIKit

extension UserDefaults {
  func colorForKey(key: String) -> UIColor? {
    var result: UIColor?
    if let cd = data(forKey: key) {
      do {
        if let color = try NSKeyedUnarchiver.unarchiveTopLevelObjectWithData(cd) as? UIColor {
          result = color
        }
      }
      catch {
        print("Error UserDefaults")
      }
    }
    return result
  }
  
  func setColor(color: UIColor?, forKey key: String) {
    var cd: NSData?
    if let color = color {
      do {
        let info = try NSKeyedArchiver.archivedData(withRootObject: color, requiringSecureCoding: false) as NSData?
        cd = info
      }
      catch {
        print("Error UserDefaults")
      }
    }
    set(cd, forKey: key)
  }
}


class SettingVC: UIViewController {

    @IBAction func blue_button(_ sender: Any) {
        blue()
    }
    @IBAction func darker_gray(_ sender: Any) {
        darker_grey()
    }
    @IBAction func med_dark_gray(_ sender: Any) {
        med_dark_grey()
    }
    @IBAction func med_light_gray(_ sender: Any) {
        med_light_grey()
    }
    @IBAction func lighter_gray(_ sender: Any) {
        lighter_grey()
    }
    @IBAction func lightest_gray(_ sender: Any) {
        lightest_grey()
    }
    @IBAction func darkest_gray(_ sender: Any) {
        darkest_grey()
    }
    @IBAction func Green(_ sender: Any) {
        green()
    }
    @IBAction func Purple(_ sender: Any) {
        purple()
    }
    @IBAction func Orange(_ sender: Any) {
        orange()
    }
    @IBAction func Teal(_ sender: Any) {
        teal()
    }
    @IBAction func Indigo(_ sender: Any) {
        indigo()
    }
    @IBAction func Red(_ sender: Any) {
        red()
    }
    @IBAction func Yellow(_ sender: Any) {
        yellow()
    }
    @IBAction func Pink(_ sender: Any) {
        pink()
    }
    @IBAction func White(_ sender: Any) {
        white()
    }
    
    
    
    
    
    
    
    
    @IBOutlet weak var ScrollView: UIScrollView!
    override func viewDidLoad() {
        super.viewDidLoad()
        view.removeConstraints(view.constraints)
        view.translatesAutoresizingMaskIntoConstraints = true
        ScrollView.removeConstraints(ScrollView.constraints)
        ScrollView.translatesAutoresizingMaskIntoConstraints = true
        view.backgroundColor = UIColor.systemRed
        ScrollView.contentSize = CGSize(width: 1000, height: 1430)
        
    }
    
    func scrollViewDidScroll(_ scrollView: UIScrollView) {
        if scrollView.contentOffset.x != 0 {
            scrollView.contentOffset.x = 0
        }
    }
    
    func blue(){
        UserDefaults.standard.setColor(color: .systemBlue, forKey: "myColor")
    }
    func darker_grey(){
        UserDefaults.standard.setColor(color: .systemGray2, forKey: "myColor")
    }
    func med_dark_grey(){
        UserDefaults.standard.setColor(color: .systemGray3, forKey: "myColor")
    }
    func med_light_grey(){
        UserDefaults.standard.setColor(color: .systemGray4, forKey: "myColor")
    }
    func lighter_grey(){
        UserDefaults.standard.setColor(color: .systemGray5, forKey: "myColor")
    }
    func lightest_grey(){
        UserDefaults.standard.setColor(color: .systemGray6, forKey: "myColor")
    }
    func darkest_grey(){
        UserDefaults.standard.setColor(color: .systemGray, forKey: "myColor")
    }
    func green(){
        UserDefaults.standard.setColor(color: .systemGreen, forKey: "myColor")
    }
    func orange(){
        UserDefaults.standard.setColor(color: .systemOrange, forKey: "myColor")
    }
    func purple(){
        UserDefaults.standard.setColor(color: .systemPurple, forKey: "myColor")
    }
    func teal(){
        UserDefaults.standard.setColor(color: .systemTeal, forKey: "myColor")
    }
    func indigo(){
        UserDefaults.standard.setColor(color: .systemIndigo, forKey: "myColor")
    }
    func red(){
        UserDefaults.standard.setColor(color: .systemRed, forKey: "myColor")
    }
    func yellow(){
        UserDefaults.standard.setColor(color: .systemYellow, forKey: "myColor")
    }
    func pink(){
        UserDefaults.standard.setColor(color: .systemPink, forKey: "myColor")
    }
    func white(){
        UserDefaults.standard.setColor(color: .systemBackground, forKey: "myColor")
    }
    
    
    

    override func viewWillLayoutSubviews() {
     super.viewWillLayoutSubviews()
     let safeFrame = view.safeAreaLayoutGuide.layoutFrame
     ScrollView.frame = safeFrame
    }

}

