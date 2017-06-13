CREATE TABLE IF NOT EXISTS `project`.`user` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `national_id` VARCHAR(15),
  `password` VARCHAR(255),
  `name` VARCHAR(255),
  `gender` VARCHAR(15),
  `address` VARCHAR(255),
  `phone` VARCHAR(31),
  `finger_data` BLOB,
  PRIMARY KEY (id)
);
