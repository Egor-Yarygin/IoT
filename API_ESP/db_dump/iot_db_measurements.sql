-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: localhost    Database: iot_db
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
-- Table structure for table `measurements`
--

DROP TABLE IF EXISTS `measurements`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `measurements` (
  `id` int NOT NULL AUTO_INCREMENT,
  `value` float NOT NULL,
  `location` varchar(255) NOT NULL,
  `device_id` varchar(255) NOT NULL,
  `timestamp` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `measurements`
--

LOCK TABLES `measurements` WRITE;
/*!40000 ALTER TABLE `measurements` DISABLE KEYS */;
INSERT INTO `measurements` VALUES (1,25,'living_room','device_1','2024-06-06 20:57:40'),(2,26.5,'kitchen','device_2','2024-06-06 20:57:40'),(3,24.8,'bedroom','device_3','2024-06-06 20:57:40'),(4,23.2,'bathroom','device_4','2024-06-06 20:57:40'),(5,27.3,'garage','device_5','2024-06-06 20:57:40'),(6,23.5,'living_room','14718881','1970-01-02 16:28:25'),(7,23.5,'living_room','14718881','1970-01-03 09:14:10'),(8,23.5,'living_room','14718881','1970-01-04 02:00:21'),(9,23.5,'living_room','14718881','1970-01-04 18:47:50'),(10,23.5,'living_room','14718881','1970-01-01 01:35:41'),(11,23.5,'living_room','14718881','1970-01-01 18:24:02'),(12,23.5,'living_room','14718881','1970-01-02 11:10:22'),(13,23.5,'living_room','14718881','1970-01-01 02:45:11'),(14,23.5,'living_room','14718881','1970-01-01 01:44:55'),(15,23.5,'living_room','14718881','1970-01-01 18:34:07'),(16,25,'living_room','14718881','1970-01-01 18:15:12'),(17,35,'living_room','14718881','1970-01-03 20:14:18'),(18,0,'string','string','2024-06-06 15:46:52'),(19,48,'bedroom','348520','2024-06-06 23:52:52'),(20,23.5,'living_room','14718881','1970-01-01 01:27:42'),(21,25,'living_room','14718881','1970-01-01 23:23:24'),(22,23.5,'living_room','14718881','1970-01-01 01:28:38'),(23,32.6,'living_room','14718881','1970-01-01 11:57:17'),(24,23.5,'living_room','14718881','1970-01-01 01:28:56'),(25,23.5,'living_room','14718881','1970-01-01 01:29:03'),(26,23.5,'bedroom','14718881','1970-01-01 05:10:18'),(27,36.6,'bedroom','14718881','1970-01-01 11:43:38'),(28,23.5,'living_room','14718881','1970-01-01 01:21:49'),(29,23.5,'living_room','14718881','1970-01-01 01:21:47'),(30,23.5,'garage','14718881','1970-01-01 16:13:31'),(31,23.5,'garage','14718881','1970-01-02 04:20:18'),(32,29.7,'bedroom','14718881','2024-06-06 17:33:29'),(33,-1,'bedroom','14718881','2024-06-07 01:41:33'),(34,23.8,'bedroom','14718881','2024-06-07 01:42:54'),(35,26,'bedroom','14718881','2024-06-07 01:52:48'),(36,26.4,'bedroom','14718881','2024-06-07 02:13:58'),(37,23.1,'bedroom','14718881','2024-06-07 02:14:20'),(38,9,'bedroom','14718881','2024-06-07 02:19:15'),(39,28.4,'kitchen','14718881','2024-06-07 04:41:49'),(40,0,'string','string','2024-06-06 20:42:35'),(41,29.7,'kitchen','14718881','2024-06-07 04:50:43'),(42,34.9,'kitchen','14718881','2024-06-07 04:53:47'),(43,0,'string','string','2024-06-06 20:55:00'),(44,53.8,'kitchen','14718881','2024-06-07 04:59:03'),(45,0,'string','string','2024-06-06 21:00:13');
/*!40000 ALTER TABLE `measurements` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-06-07  5:02:27
