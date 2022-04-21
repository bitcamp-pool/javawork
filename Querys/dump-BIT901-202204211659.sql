-- MySQL dump 10.13  Distrib 5.5.52, for Win64 (x86)
--
-- Host: 222.106.201.63    Database: BIT901
-- ------------------------------------------------------
-- Server version	5.5.52

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `shop`
--

DROP TABLE IF EXISTS `shop`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shop` (
  `num` smallint(6) NOT NULL AUTO_INCREMENT,
  `sangpum` varchar(50) DEFAULT NULL,
  `photo` varchar(50) DEFAULT NULL,
  `price` int(11) DEFAULT NULL,
  `color` varchar(20) DEFAULT NULL,
  `cnt` smallint(6) DEFAULT NULL,
  `ipgoday` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`num`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shop`
--

LOCK TABLES `shop` WRITE;
/*!40000 ALTER TABLE `shop` DISABLE KEYS */;
INSERT INTO `shop` VALUES (3,'남대문','../image2/5.jpg',5000,'#db14cb',3,'2022-04-04'),(5,'봄봄','../image2/6.jpg',7000,'#f2c9f8',3,'2022-04-19'),(6,'에이스체크쿠션','../image2/11.jpg',100,'#fcccff',1,'2022-04-20'),(7,'블랙코트','../image2/10.jpg',10000,'#3a363a',1,'2022-04-20'),(8,'룰루원피스','../image2/7.jpg',1000,'#ffcccc',1,'2022-04-20'),(9,'하늘원피스','../image2/3.jpg',3000,'#9ff4ee',1,'2022-04-20'),(10,'깜장원피스','../image2/2.jpg',1000,'#121212',1,'2022-04-15'),(12,'땡땡이','../image2/4.jpg',1000,'#22111a',1,'2022-04-18'),(13,'xxx','../image2/1.jpg',1000,'#ffcccc',1,'2022-04-20'),(14,'꼬까','../image2/7.jpg',9000,'#11e493',1,'2022-04-11');
/*!40000 ALTER TABLE `shop` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stu`
--

DROP TABLE IF EXISTS `stu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stu` (
  `num` smallint(6) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL,
  `photo` varchar(50) DEFAULT NULL,
  `hp` varchar(20) DEFAULT NULL,
  `addr` varchar(50) DEFAULT NULL,
  `writeday` datetime DEFAULT NULL,
  PRIMARY KEY (`num`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stu`
--

LOCK TABLES `stu` WRITE;
/*!40000 ALTER TABLE `stu` DISABLE KEYS */;
INSERT INTO `stu` VALUES (1,'김우빈','../image/2.jpg','010-1234-5678','서울 강남구','2022-04-19 10:07:02'),(2,'박보영','../image/12.jpg','010-2222-5678','서울 영등포구','2022-04-19 10:07:06'),(3,'신민아','../image/17.jpg','010-8888-5678','제주도 애월읍','2022-04-19 10:07:10'),(4,'설현','../image/15.jpg','010-9999-5678','제주도 중문','2022-04-19 10:07:14'),(5,'수지','../image/19.jpg','010-5656-5678','서울 삼성동','2022-04-19 10:08:09'),(7,'강동원','../image/9.jpg','010-7777-8888','강원도 삼척','2022-04-19 10:13:12'),(11,'정용관','../image/3.jpg','010-1212-8282','인천 남동구','2022-04-19 10:48:04');
/*!40000 ALTER TABLE `stu` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'BIT901'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-04-21 16:59:05
