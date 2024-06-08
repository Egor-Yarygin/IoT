-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: localhost    Database: log_db
-- ------------------------------------------------------
-- Server version	8.0.37

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `admin_device`
--

DROP TABLE IF EXISTS `admin_device`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `admin_device` (
  `id` int NOT NULL AUTO_INCREMENT,
  `admin_name` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `ueid` varchar(75) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `ueid` (`ueid`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admin_device`
--

LOCK TABLES `admin_device` WRITE;
/*!40000 ALTER TABLE `admin_device` DISABLE KEYS */;
INSERT INTO `admin_device` VALUES (1,'danya','$2b$12$hp8sALHhnpylwC5OZWPk8u5ti0DhkTf8z167Ux7CR5pmCO0w/gP9a','r32r32r32r32'),(2,'poc','$2b$12$eIoXJhKSyQONz9RzbFMwWuPRbLfxpmLKfGZYcNLPfTy4OdmAP5O/.','8534dsaf32');
/*!40000 ALTER TABLE `admin_device` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rfid_keys`
--

DROP TABLE IF EXISTS `rfid_keys`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `rfid_keys` (
  `id` int NOT NULL AUTO_INCREMENT,
  `ueid` varchar(75) NOT NULL,
  `uid` varchar(255) NOT NULL,
  `user` varchar(255) NOT NULL,
  `permission` enum('YES','NO') NOT NULL,
  PRIMARY KEY (`id`),
  KEY `ueid` (`ueid`),
  CONSTRAINT `rfid_keys_ibfk_1` FOREIGN KEY (`ueid`) REFERENCES `admin_device` (`ueid`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `rfid_keys`
--

LOCK TABLES `rfid_keys` WRITE;
/*!40000 ALTER TABLE `rfid_keys` DISABLE KEYS */;
INSERT INTO `rfid_keys` VALUES (12,'r32r32r32r32','0x83, 0x43, 0xad, 0x95','danek','YES'),(14,'8534dsaf32','0xf3, 0xfe, 0x88, 0xa6','testf','YES');
/*!40000 ALTER TABLE `rfid_keys` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-06-08 12:11:26
