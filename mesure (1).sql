-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Client :  localhost:3306
-- Généré le :  Jeu 08 Avril 2021 à 10:55
-- Version du serveur :  10.0.28-MariaDB-2+b1
-- Version de PHP :  7.3.27-1~deb10u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `mesure`
--

-- --------------------------------------------------------

--
-- Structure de la table `Mesure_Table`
--

CREATE TABLE `Mesure_Table` (
  `ID` bigint(20) UNSIGNED NOT NULL,
  `M_distance` varchar(25) DEFAULT NULL,
  `M_date` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `Mesure_Table`
--

INSERT INTO `Mesure_Table` (`ID`, `M_distance`, `M_date`) VALUES
(1114, '9', '21-4-4 9:45'),
(1115, '9', '21-4-4 9:46'),
(1116, '6', '21-4-5 5:52'),
(1117, '8', '21-4-5 5:52'),
(1118, '8', '21-4-5 6:59'),
(1119, '6', '21-4-5 6:59'),
(1120, '5', '21-4-5 6:59'),
(1121, '8', '21-4-5 7:10'),
(1122, '9', '21-4-5 7:10'),
(1123, '7', '21-4-5 7:10'),
(1124, '6', '21-4-5 7:10');

--
-- Index pour les tables exportées
--

--
-- Index pour la table `Mesure_Table`
--
ALTER TABLE `Mesure_Table`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `Mesure_Table`
--
ALTER TABLE `Mesure_Table`
  MODIFY `ID` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1125;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
